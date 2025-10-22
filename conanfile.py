"""Conan package configuration for Tablr library."""

from typing import Any
from conan import ConanFile  # type: ignore[import-untyped]
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout  # type: ignore[import-untyped]


class TablrConan(ConanFile):  # type: ignore[misc]
    """Tablr data manipulation library Conan package."""

    name: str = "tablr"
    version: str = "0.0.1"
    license: str = "Apache-2.0"
    author: str = "Muhammad Fiaz contact@muhammadfiaz.com"
    url: str = "https://github.com/muhammad-fiaz/tablr"
    description: str = "Fastest and simpler data manipulation library for C/C++ with multi-device support"
    topics: tuple[str, ...] = ("dataframe", "data-manipulation", "c", "cpp", "cuda", "gpu")
    settings: Any = "os", "compiler", "build_type", "arch"
    options: Any = {
        "shared": [True, False],
        "fPIC": [True, False],
        "cuda": [True, False],
        "xpu": [True, False],
        "npu": [True, False],
        "tpu": [True, False]
    }
    default_options: Any = {
        "shared": False,
        "fPIC": True,
        "cuda": False,
        "xpu": False,
        "npu": False,
        "tpu": False
    }
    exports_sources: tuple[str, ...] = ("CMakeLists.txt", "src/*", "include/*")

    def config_options(self) -> None:
        """Configure package options based on platform."""
        # pylint: disable=no-member
        if hasattr(self.settings, "os") and str(self.settings.os) == "Windows":
            if hasattr(self.options, "fPIC"):
                delattr(self.options, "fPIC")

    def layout(self) -> None:
        """Define package layout."""
        cmake_layout(self)

    def generate(self) -> None:
        """Generate build system files."""
        tc = CMakeToolchain(self)
        # pylint: disable=no-member
        if hasattr(self.options, "cuda") and self.options.cuda:
            tc.variables["TABLR_CUDA_SUPPORT"] = "ON"
        if hasattr(self.options, "xpu") and self.options.xpu:
            tc.variables["TABLR_XPU_SUPPORT"] = "ON"
        if hasattr(self.options, "npu") and self.options.npu:
            tc.variables["TABLR_NPU_SUPPORT"] = "ON"
        if hasattr(self.options, "tpu") and self.options.tpu:
            tc.variables["TABLR_TPU_SUPPORT"] = "ON"
        tc.generate()

    def build(self) -> None:
        """Build the library."""
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self) -> None:
        """Package the library."""
        cmake = CMake(self)
        cmake.install()

    def package_info(self) -> None:
        """Define package information."""
        self.cpp_info.libs = ["tablr"]
