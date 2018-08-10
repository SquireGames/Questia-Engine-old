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
        "shared=True", "gtest:shared=True", "glfw:shared=True", "glad:shared=True", 
        "build_doc=False", 
        "build_samples=False",
        "build_tests=False",
        "glad:profile=core", "glad:api_type=gl", "glad:api_version=3.3", "glad:spec=gl", "glad:no_loader=False")
    generators = "cmake"
    requires = (
         "glfw/3.2.1.20180327@bincrafters/stable", 
         "glad/0.1.24@bincrafters/stable")

    def requirements(self):
        if self.options.build_tests:
            self.requires("gtest/1.8.0@bincrafters/stable")
            self.options["gtest"].shared = self.options.shared

    def configure(self):
        for req in self.requires:
            self.options[req.split("/", 1)[0]].shared = self.options.shared
        # do not allow non-static tests on Unix systems
        if self.settings.os != "Windows" and self.options.build_tests and not self.options.shared:
            raise Exception("Cannot test this package when linking statically. Use shared=True or build_tests=False.")
        # ensure proper compiler settings when using Visual Studio
        if self.settings.compiler == "Visual Studio":
            if self.options.shared and self.settings.build_type == "Debug" and self.settings.compiler.runtime != "MDd":
                self.output.warn("Use '-s compiler.runtime=MDd' when compiling with shared=true and build_type=Debug")
            elif self.options.shared and self.settings.build_type == "Release" and self.settings.compiler.runtime != "MD":
                self.output.warn("Use '-s compiler.runtime=MD' when compiling with shared=true and build_type=Release")
            elif not self.options.shared and self.settings.build_type == "Debug" and self.settings.compiler.runtime != "MTd":
                self.output.warn("Use '-s compiler.runtime=MTd' when compiling with shared=false and build_type=Debug")
            elif not self.options.shared and self.settings.build_type == "Release" and self.settings.compiler.runtime != "MT":
                self.output.warn("Use '-s compiler.runtime=MT' when compiling with shared=false and build_type=Release")

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
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

    def imports(self):
        if self.options.shared:
            self.copy("*.dll", "bin", "bin")
            self.copy("*.dylib*", "lib", "lib")
