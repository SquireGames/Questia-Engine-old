from conans import ConanFile, CMake, tools


class QengConan(ConanFile):
    name = "QENG"
    version = "0.0.1"
    folder = "Questia-Engine"
    license = "https://github.com/SquireGames/Questia-Engine/blob/master/LICENSE.txt"
    url = "https://github.com/SquireGames/Questia-Engine"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True", "gtest:shared=True"
    generators = "cmake"
    requires = "gtest/1.8.0@bincrafters/stable"

    def configure(self):
        for req in self.requires:
            self.options[req.split('/', 1)[0]].shared = self.options.shared
    
    def source(self):
        self.run("git clone https://github.com/SquireGames/Questia-Engine.git")
        self.run("cd Questia-Engine")  

    def build(self):
        cmake = CMake(self)
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
        self.cpp_info.libs = self.collect_libs()
              
    def imports(self):
        if self.options.shared == True:
            self.copy("*.dll", "bin", "bin")
            self.copy("*.dylib", "lib", "lib")
    