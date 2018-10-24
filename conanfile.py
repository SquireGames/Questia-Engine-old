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
        "build_tests": [True, False],
        "graphics": ["none", "opengl"]}
    default_options = (
        "shared=True",
        "build_doc=False", 
        "build_samples=False",
        "build_tests=False",
        "graphics=opengl")
    generators = "cmake"
    requires = ()
    exports_sources = "cmake/*", "doc*", "include*", "samples*", "src*", "test*", "CMakeLists.txt"

    def requirements(self):
        if self.options.build_tests:
            self.requires("gtest/1.8.0@bincrafters/stable")
            self.options["gtest"].shared = self.options.shared
        if self.options.graphics == "opengl":
            self.requires("glad/0.1.24@bincrafters/stable")
            self.requires("glfw/3.2.1.20180327@bincrafters/stable")
            self.options["glad"].shared = self.options.shared
            self.options["glfw"].shared = self.options.shared
            self.options["glad"].profile = "core"
            self.options["glad"].api_type = "gl"
            self.options["glad"].api_version = "3.3"
            self.options["glad"].spec = "gl"
            self.options["glad"].no_loader = False
            self.options["glad"].extensions = ""

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

        # make defines easier to use in IDEs when just installing the project
        self.deps_cpp_info.defines.extend(["QENG_VERSION_MAJOR=" + self.version.split(".")[0],
                                           "QENG_VERSION_MINOR=" + self.version.split(".")[1],
                                           "QENG_VERSION_PATCH=" + self.version.split(".")[2],
                                           "BUILD_DOC=" + str(self.options.build_doc),
                                           "QENG_BUILD_SAMPLES=" + str(self.options.build_samples),
                                           "QENG_BUILD_TESTS=" + str(self.options.build_tests),
                                           "QENG_GRAPHICS=" + str(self.options.graphics)])

    def build(self):
        cmake = CMake(self)
        cmake.definitions["QENG_VERSION_MAJOR"] = self.version.split(".")[0]
        cmake.definitions["QENG_VERSION_MINOR"] = self.version.split(".")[1]
        cmake.definitions["QENG_VERSION_PATCH"] = self.version.split(".")[2]
        cmake.definitions["BUILD_DOC"] = self.options.build_doc
        cmake.definitions["QENG_BUILD_SAMPLES"] = self.options.build_samples
        cmake.definitions["QENG_BUILD_TESTS"] = self.options.build_tests
        cmake.definitions["QENG_GRAPHICS"] = self.options.graphics
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
        self.cpp_info.release_shared.libs = ["qeng"]
        self.cpp_info.release_static.libs = ["qeng-s"]
        self.cpp_info.debug_shared.libs = ["qeng-d"]
        self.cpp_info.debug_static.libs = ["qeng-s-d"]

    def imports(self):
        if self.options.shared:
            self.copy("*.dll", "bin", "bin")
            self.copy("*.dylib*", "lib", "lib")
            self.copy('*.so*', dst='lib', src='lib')
