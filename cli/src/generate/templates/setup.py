from os.path import join
from setuptools import Extension, find_packages, setup
from setuptools.command.build import build
from wheel.bdist_wheel import bdist_wheel


class Build(build):
    def run(self):
        dest = join(self.build_lib, "tree_sitter_PARSER_NAME", "queries")
        try:
            self.copy_tree("queries", dest)
        except:
            pass
        super().run()


class BdistWheel(bdist_wheel):
    def get_tag(self):
        python, abi, platform = super().get_tag()
        if python.startswith("cp"):
            python, abi = "cp38", "abi3"
        return python, abi, platform


setup(
    packages=find_packages("bindings/python"),
    package_dir={"": "bindings/python"},
    package_data={
        "tree_sitter_LOWER_PARSER_NAME": ["*.pyi", "py.typed"],
        "tree_sitter_LOWER_PARSER_NAME.queries": ["*.scm"],
    },
    ext_package="tree_sitter_LOWER_PARSER_NAME",
    ext_modules=[
        Extension(
            name="_binding",
            sources=[
                "bindings/python/tree_sitter_LOWER_PARSER_NAME/binding.c",
                "src/parser.c",
                # NOTE: if your language uses an external scanner, add it here.
            ],
            extra_compile_args=["-std=c11"],
            define_macros=[("Py_LIMITED_API", "0x03080000"), ("PY_SSIZE_T_CLEAN", None)],
            include_dirs=["src"],
            py_limited_api=True,
        )
    ],
    cmdclass={"build": Build, "bdist_wheel": BdistWheel},
    zip_safe=False,
)
