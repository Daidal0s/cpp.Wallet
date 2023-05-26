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

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Wallet.c++", nullptr, nullptr);
	if (window == nullptr)
		return 1;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);										// Включить vsync

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;		 // Включить навиггацию по клавиатуре
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;			 // Подрубаем доки

	ImGui::StyleColorsDark();

	// Настройка платформы
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	AccountsList _accountList;

	static bool show_createAccountWindow = false;
	static bool show_demo_window = false;

	static bool show_accounts = false;
	static bool show_billMenu = false;
	static bool show_billsList = true;

	if (!IO::checkForSave())
		show_createAccountWindow = true;
	else
		IO::loadAccounts(_accountList);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Включение возможности состыковки
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		// Верхнее меню окна
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save Accounts")) { IO::saveAccounts(_accountList); }
				if (ImGui::MenuItem("Load Accounts")) { IO::loadAccounts(_accountList); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Accounts"))
			{
				if (ImGui::MenuItem("Create Account", NULL, &show_createAccountWindow)) { }
				if (ImGui::MenuItem("Show Accounts", NULL, &show_accounts)) { }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Bills"))
			{
				if (ImGui::MenuItem("Open Bill Menu", NULL, &show_billMenu)) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// Открыть окно создания аккаунтов
		if (show_createAccountWindow)
			ImGui::CreateAccount(_accountList, &show_createAccountWindow);

		// Открыть меню счетов
		if (show_billMenu)
			ImGui::BillWindow(_accountList, &show_billMenu);

		// Показать аккаунты
		if (show_accounts)
			ImGui::Accounts(_accountList, &show_accounts);

		// Демо-окно
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// Рендер
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Очистка
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}