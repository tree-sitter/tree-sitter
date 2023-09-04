from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import get, apply_conandata_patches, export_conandata_patches, collect_libs
from conans.tools import Git


class Pkg(ConanFile):
    name = "tree-sitter"
    version = "0.20.8"
    description = "Tree-sitter fork"
    url = "https://gitlab.tcsbank.ru/search-tech/tree-sitter"
    license = "MIT-1.0"
    settings = "os", "compiler", "build_type", "arch"

    user = "cpp-core"
    channel = "stable"
    package_type = "static-library"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
    }
    requires = []
    
    @property
    def _source_subfolder(self):
        return "source_subfolder"

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self, src_folder="lib")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def source(self):
        git = Git(folder=self._source_subfolder)
        git.clone("https://github.com/Gornak40/tree-sitter.git", "tree-sitter", shallow=True)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", self.name)
        self.cpp_info.set_property("cmake_target_name", f"{self.name}::{self.name}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.libs = collect_libs(self)
