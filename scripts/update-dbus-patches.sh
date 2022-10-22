#!/bin/sh
set -e

git diff --no-index src/worker/dbus.orig src/worker/dbus > ./scripts/dbus-patches.diff
