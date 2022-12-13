del "..\WalnutApp.sln"
rd /s /q "..\bin-int"

del "..\Walnut\Walnut.vcxproj"
del "..\Walnut\Walnut.vcxproj.user"
del "..\Walnut\Walnut.vcxproj.filters"
rd /s /q "..\Walnut\bin"

del "..\WalnutApp\WalnutApp.vcxproj"
del "..\WalnutApp\WalnutApp.vcxproj.user"
del "..\WalnutApp\WalnutApp.vcxproj.filters"
rd /s /q "..\WalnutApp\bin"

del "..\vendor\imgui\ImGui.vcxproj"
rd /s /q "..\vendor\imgui\bin"
rd /s /q "..\vendor\imgui\bin-int"

del "..\vendor\glfw\GLFW.vcxproj"
del "..\vendor\glfw\GLFW.vcxproj.filters"
rd /s /q "..\vendor\glfw\bin"
rd /s /q "..\vendor\glfw\bin-int"

del "..\vendor\glew\GLEW.vcxproj"
del "..\vendor\glew\GLEW.vcxproj.filters"
rd /s /q "..\vendor\glew\bin"
rd /s /q "..\vendor\glew\bin-int"

del "..\vendor\assimp\assimp.vcxproj"
del "..\vendor\assimp\assimp.vcxproj.filters"
rd /s /q "..\vendor\assimp\bin"
rd /s /q "..\vendor\assimp\bin-int"

PAUSE