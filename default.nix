{ pkgs ? import
    (
      builtins.fetchTarball {
        url = "https://github.com/NixOS/nixpkgs/archive/902d91def1efbea804f5158e5999cb113cedf04b.tar.gz";
        sha256 = "sha256:1ya19ix77k2yn1c2gyzz644576c2qn11llrqhyy0c7a3y4dlwnn9";
      }
    )
    { }
, clangSupport ? true
}:

with pkgs;

python3Packages.callPackage ./derivation.nix {
  src = ./.;
  stdenv = if clangSupport then clangStdenv else gccStdenv;
  mdot = callPackage ../mdot/derivation.nix {
    src = ./mdot/.;
    stdenv = if clangSupport then clangStdenv else gccStdenv;
  };
}
