{ stdenv
, buildPythonPackage ? null
, boost17x
, cmakeMinimal
, lapack
, mdot
, ninja
, numpy ? null
, pybind11 ? null
, pytest ? null
, src ? "./."
, tbb
, version ? "0.0.1"
}:

buildPythonPackage {
  name = "mdotbind-${version}";
  inherit version;
  inherit src;

  format = "other";

  nativeBuildInputs = [ cmakeMinimal ninja ];
  buildInputs = [ boost17x mdot pybind11 lapack tbb ];
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
    # export PYTHONPATH=$out/lib/python3.9/site-packages:$$PYTHONPATH
  '';
}
