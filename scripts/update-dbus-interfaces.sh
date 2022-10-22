#!/bin/sh
# Updates dbus interfaces for systemd.
# This requires Nix to be installed, and to have a Nixpkgs channel set up.
set -e

echo "Grabbing systemd from nix..."
SYSTEMD_PREFIX=$(nix-build '<nixpkgs>' -A systemd --no-out-link)

echo "Copying dbus introspection files..."
DBUS_SOURCE_DIR="src/worker/dbus"
DBUS_SOURCE_ORIG_DIR="src/worker/dbus.orig"
mkdir -p "${DBUS_SOURCE_DIR}"
rm -f "${DBUS_SOURCE_DIR}"/*.xml
cp  --no-preserve=all \
    "${SYSTEMD_PREFIX}/share/dbus-1/interfaces"/*.xml \
    "${DBUS_SOURCE_DIR}"

echo "Workaround: avoiding name collisions in qdbusxml2cpp..."
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.login1.Manager.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.login1.LoginManager.xml"
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.import1.Manager.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.import1.ImportManager.xml"
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.machine1.Manager.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.machine1.MachineManager.xml"
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.network1.Manager.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.network1.NetworkManager.xml"
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.oom1.Manager.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.oom1.OomManager.xml"
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.resolve1.Manager.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.resolve1.ResolveManager.xml"
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.network1.Link.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.network1.NetworkLink.xml"
mv  "${DBUS_SOURCE_DIR}/org.freedesktop.resolve1.Link.xml" \
    "${DBUS_SOURCE_DIR}/org.freedesktop.resolve1.ResolveLink.xml"

echo "Workaround: moving duplicate DBus interfaces out of service files..."
for i in "${DBUS_SOURCE_DIR}"/*.xml; do
    perl -0777 -i -pe 's| <interface name=\"org.freedesktop.DBus.*?</interface>\n||gs' "$i"
done
cp scripts/org.freedesktop.DBus.xml "${DBUS_SOURCE_DIR}"

echo "Making a copy of the processed, unpatched interfaces..."
mkdir -p "${DBUS_SOURCE_ORIG_DIR}"
rm -f "${DBUS_SOURCE_ORIG_DIR}"/*.xml
cp "${DBUS_SOURCE_DIR}"/*.xml "${DBUS_SOURCE_ORIG_DIR}"

echo "Applying manual patches..."
patch -p1 -i ./scripts/dbus-patches.diff

echo "Generating interface list for CMakeLists.txt..."
DBUS_INTERFACE_LIST_OLD="# BEGIN DBUS INTERFACE LIST\\n.*\\n# END DBUS INTERFACE LIST"
DBUS_INTERFACE_LIST_NEW="# BEGIN DBUS INTERFACE LIST
# autogenerated by update-dbus-interfaces.sh
$(ls ${DBUS_SOURCE_DIR} | sort | sed "s|^|  ${DBUS_SOURCE_DIR}/|")
# END DBUS INTERFACE LIST"

echo "Writing interface list to CMakeLists.txt..."
cp CMakeLists.txt CMakeLists.bak
perl -0777 -i -pe "s|$DBUS_INTERFACE_LIST_OLD|$DBUS_INTERFACE_LIST_NEW|s" CMakeLists.txt

echo "Done."
exit 0
