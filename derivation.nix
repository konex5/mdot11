{ stdenv
, buildPythonPackage ? null
, src
, boost17x
, cmakeMinimal
, ninja
, numpy ? null
, pybind11 ? null
, pytest ? null
, sphinx ? null
, sphinx_rtd_theme ? null
, tbb
}:
let
  version = "0.0.0";
in
{

  libfhmdot = stdenv.mkDerivation {
    name = "libfhmdot";
    inherit src version;

    nativeBuildInputs = [ cmakeMinimal ninja ];
    buildInputs = [ boost17x tbb ];

    cmakeFlags = [
      "-DCMAKE_BUILD_TYPE=Release"
      "-DPROJECT_TESTS=On"
      "-DPROJECT_SANDBOX=OFF"
      "-DPROJECT_PYTHON=OFF"
    ];
    ninjaFlags = [ "-v" ];
    makeFlags = [ "VERBOSE=1" ];

    enableParallelBuilding = true;
    enableParallelChecking = true;

    installPhase = "ninja install";
    outputs = ["out" "include" "lib"];
  };

  pyfhmdot = buildPythonPackage {
    pname = "pyfhmdot";
    version = "0.0.0";
    format = "other";
    inherit src;

    nativeBuildInputs = [ cmakeMinimal ninja ];
    buildInputs = [ boost17x pybind11 tbb ];
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
  };
}
