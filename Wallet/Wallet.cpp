#include "stdafx.h"
#include "imgui_walletGui.h"


static void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error" << error << ": " << description << "\n";
}

int main()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Wallet.c++", nullptr, nullptr);
	if (window == nullptr)
		return 1;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);										// Enable vsync

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;		 // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;			// Подрубаем доки

	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	AccountsList _accountList;

	// Our state
	bool show_createAccount_window = false;
	bool show_demo_window = true;
	bool show_accounts = true;


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Accounts"))
			{
				if (ImGui::MenuItem("Create Account", NULL, &show_createAccount_window)) {}
				if (ImGui::MenuItem("Show Accounts"), NULL, &show_accounts) {}
				if (ImGui::MenuItem("Save Accounts")) { IO::saveAccounts(_accountList); }
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (show_createAccount_window)
			ImGui::CreateAccount(_accountList, &show_createAccount_window);
		/*if (!IO::checkForSave())
		{
			ImGui::CreateAccount(_accountList);
		}*/

		if (show_accounts)
			for (int32_t iii = 0; iii < _accountList.getNumberOfAccounts(); ++iii)
				ImGui::AccountGenerator(_accountList, iii, &show_accounts);

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}