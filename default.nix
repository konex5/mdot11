{ pkgs ? import
    (
      builtins.fetchTarball {
        url = "https://github.com/NixOS/nixpkgs/archive/902d91def1efbea804f5158e5999cb113cedf04b.tar.gz";
        sha256 = "sha256:1ya19ix77k2yn1c2gyzz644576c2qn11llrqhyy0c7a3y4dlwnn9";
      }
    )
    { }
, mdotPath
, clangSupport ? true
}:

with pkgs;

python3Packages.callPackage ./derivation.nix {
  stdenv = if clangSupport then clangStdenv else gccStdenv;
  mdot = callPackage ../mdot/derivation.nix {
    stdenv = if clangSupport then clangStdenv else gccStdenv;

    src = fetchgit {
      url = mdotPath;
      sha256 = "sha256-P/SZ2/3rErb3YQomF/rBtpZRq2UKLBj3f5a+uTxH7fU=";
      rev = "v0.0.3";
    };
  };
}
