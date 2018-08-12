from conans import ConanFile, CMake, tools


class QengConan(ConanFile):
    name = "qeng"
    version = "0.0.1"
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
         
    exports_sources = "*", "!build*", "!test_package*", "!.*", "!conanfile.py"

    def requirements(self):
        if self.options.build_tests:
            self.requires("gtest/1.8.0@bincrafters/stable")
            self.options["gtest"].shared = self.options.shared

    def configure(self):
        for req in self.requires:
            self.options[req.split("/", 1)[0]].shared = self.options.shared
        
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

    def build(self):
        cmake = CMake(self)
        cmake.definitions["QENG_VERSION_MAJOR"] = self.version.split(".")[0]
        cmake.definitions["QENG_VERSION_MINOR"] = self.version.split(".")[1]
        cmake.definitions["QENG_VERSION_PATCH"] = self.version.split(".")[2]
        cmake.definitions["BUILD_DOC"] = self.options.build_doc
        cmake.definitions["QENG_BUILD_SAMPLES"] = self.options.build_samples
        cmake.definitions["QENG_BUILD_TESTS"] = self.options.build_tests
        cmake.configure()
        cmake.build()
        cmake.install()

    def package(self):
        self.copy("*.h", dst="include", src="include")
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
            self.copy('*.so*', dst='lib', src='lib')
