{ pkgs ? import
    (
      builtins.fetchTarball {
        url = "https://github.com/NixOS/nixpkgs/archive/c00959877fb06b09468562518b408acda886c79e.tar.gz";
        sha256 = "sha256:02anj9mbzy45bszlmv7k42mb5y7yj2lxc5vpbxgd3f5qljn5ih7y";
      }
    )
    { }
, clangSupport ? true
}:

with pkgs;
with python3Packages;

callPackage ./derivation.nix {
  stdenv = if clangSupport then clangStdenv else gccStdenv;
}


