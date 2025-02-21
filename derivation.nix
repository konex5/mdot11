{ stdenv
, buildPythonPackage ? null
, boost17x
, cmakeMinimal
, mdot
, ninja
, numpy ? null
, pybind11 ? null
, pytest ? null
, python ? null
, src ? ./.
}:
let
  version = "0.0.0";
in
#{

  # libfhmdot = stdenv.mkDerivation {
  #   name = "libfhmdot";
  #   inherit src version;

  #   nativeBuildInputs = [ cmakeMinimal ninja ];
  #   buildInputs = [ boost17x tbb ];

  #   cmakeFlags = [
  #     "-DCMAKE_BUILD_TYPE=Release"
  #     "-DPROJECT_TESTS=On"
  #     "-DPROJECT_SANDBOX=OFF"
  #     "-DPROJECT_PYTHON=OFF"
  #   ];
  #   ninjaFlags = [ "-v" ];
  #   makeFlags = [ "VERBOSE=1" ];

  #   enableParallelBuilding = true;
  #   enableParallelChecking = true;

  #   installPhase = "ninja install";
  # };

  #  pyfhmdot =

buildPythonPackage rec {
  name = "pyfhmdot";
  inherit src;

  format = "other";

  nativeBuildInputs = [ cmakeMinimal ninja ];
  buildInputs = [ boost17x pybind11 ];
  propagatedBuildInputs = [ numpy ];
  checkInputs = [ pytest ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DPROJECT_TESTS=ON"
    "-DPROJECT_SANDBOX=OFF"
    "-DPROJECT_PRECISION_FLOAT32=OFF"
    "-DPROJECT_PYTHON=ON"
  ];
  ninjaFlags = [ "-v" ];
  makeFlags = [ "VERBOSE=1" ];

  enableParallelBuilding = true;
  enableParallelChecking = true;

  installPhase = "ninja install";

  postInstall = ''
    mkdir -p $out/${python.sitePackages}
    cp $out/bin/*.so $out/${python.sitePackages}
    export PYTHONPATH=$out/${python.sitePackages}:$PYTHONPATH
  '';
}
#}
