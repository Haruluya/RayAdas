extern RayAdas::Application* RayAdas::CreateApplication();



int main(int argc, char** argv)
{
	// ��ʼ����־���á�
	RayAdas::Log::Init();
	auto app = RayAdas::CreateApplication();
	app->Run();
	delete app;	
}