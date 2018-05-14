from conans import ConanFile, CMake, tools


class QengConan(ConanFile):
    name = "QENG"
    version = "0.0.1"
    folder = "Questia-Engine"
    license = "https://github.com/SquireGames/Questia-Engine/blob/master/LICENSE.txt"
    url = "https://github.com/SquireGames/Questia-Engine"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "build_doc": [True, False],
        "build_samples": [True, False],
        "build_tests": [True, False]}
    default_options = (
        "shared=True", "gtest:shared=True", "glfw:shared=True", "glad:shared=True"
        , "build_doc=False"
        , "build_samples=False"
        , "build_tests=False"
        , "glad:profile=core", "glad:api_type=gl", "glad:api_version=3.3", "glad:spec=gl", "glad:no_loader=False")
    generators = "cmake"
    requires = (
        "gtest/1.8.0@bincrafters/stable"
        , "glfw/3.2.1.20180327@bincrafters/stable"
        , "glad/0.1.16a0@bincrafters/stable")

    def configure(self):
        for req in self.requires:
            self.options[req.split("/", 1)[0]].shared = self.options.shared

    def source(self):
        self.run("git clone https://github.com/SquireGames/Questia-Engine.git")
        self.run("cd %s" % self.folder)

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_DOC"] = self.options.build_doc
        cmake.definitions["QENG_BUILD_SAMPLES"] = self.options.build_samples
        cmake.definitions["QENG_BUILD_TESTS"] = self.options.build_tests
        cmake.configure()
        cmake.build()
        cmake.install()

    def package(self):
        self.copy("*.h", dst="include", src=self.folder)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

    def imports(self):
        if self.options.shared:
            self.copy("*.dll", "bin", "bin")
            self.copy("*.dylib", "lib", "lib")
