"""Conan package configuration for Tablr library."""

from typing import Any
from conan import ConanFile  # type: ignore[import-untyped]
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout  # type: ignore[import-untyped]


class TablrConan(ConanFile):  # type: ignore[misc]
    """Tablr data manipulation library Conan package."""

    name: str = "tablr"
    version: str = "0.0.0"
    license: str = "Apache-2.0"
    author: str = "Muhammad Fiaz contact@muhammadfiaz.com"
    url: str = "https://github.com/muhammad-fiaz/tablr"
    description: str = "Fastest and simpler data manipulation library for C/C++"
    topics: tuple[str, ...] = ("dataframe", "data-manipulation", "c", "cpp")
    settings: Any = "os", "compiler", "build_type", "arch"
    options: Any = {"shared": [True, False], "fPIC": [True, False]}
    default_options: Any = {"shared": False, "fPIC": True}
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
