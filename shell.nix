let pkgs = import <nixpkgs> {};
in
pkgs.mkShell {
  name = "servicecontrol";
  nativeBuildInputs = with pkgs; [
    cmake
    capnproto
  ];
  buildInputs = with pkgs; [
    qt5.qtbase
    capnproto
    libsForQt5.kdeFrameworks.extra-cmake-modules
  ];
}
