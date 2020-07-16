let
  crossPkgs = import <nixpkgs> { crossSystem = { config ="i686-elf"; }; };
  pkgs = import <nixpkgs> { };
in crossPkgs.mkShell {
  nativeBuildInputs = [ pkgs.qemu pkgs.grub2 ];
}
