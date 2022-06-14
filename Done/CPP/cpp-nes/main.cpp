#include <iostream>
//#include <portaudio.h>
#include <GLFW/glfw3.h>

#ifdef __linux__
#include "pa_linux_alsa.h"
#endif

#include "NES.h"

constexpr int AUDIO_FRAME_BUFFER_SIZE = 1024;

// NES generates 256 x 240 pixels.
// You are free to resize at runtime
// but you can also set a scale factor to init with.
// 3-5 is good.
constexpr int display_scale_factor = 4;

// Fullscreen is awesome!
// Off by default so console can be seen
// if something goes wrong.
constexpr bool fullscreen = false;

// Recommend off unless severe tearing.
constexpr bool v_sync = false;

bool getKey(GLFWwindow* window, int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

//  Keymap (modify as desired)
// -------------------------------------
//  Up/Down/Left/Right   |  Arrow Keys
//  Start                |  Enter
//  Select               |  Right Shift
//  A                    |  Z
//  B                    |  X
//  Turbo A              |  S
//  Turbo B              |  D
// -------------------------------------
//  Emulator keys:
//  Tilde                |  Fast-forward
//  Escape               |  Quit
//  ALT+F4               |  Quit
// -------------------------------------
uint8_t getKeyboard(GLFWwindow* window, bool t) {
	uint8_t result = getKey(window, GLFW_KEY_Z) || (t && getKey(window, GLFW_KEY_S));
	result |= (getKey(window, GLFW_KEY_X) || (t && getKey(window, GLFW_KEY_D))) << 1;
	result |= (getKey(window, GLFW_KEY_RIGHT_SHIFT)) << 2;
	result |= (getKey(window, GLFW_KEY_ENTER)) << 3;
	result |= (getKey(window, GLFW_KEY_UP)) << 4;
	result |= (getKey(window, GLFW_KEY_DOWN)) << 5;
	result |= (getKey(window, GLFW_KEY_LEFT)) << 6;
	result |= (getKey(window, GLFW_KEY_RIGHT)) << 7;
	return result;
}

uint8_t getJoystick(int joy, bool t) {
	if (!glfwJoystickPresent(joy)) {
		return 0;
	}
	int count;
	const float* axes = glfwGetJoystickAxes(joy, &count);
	const unsigned char* buttons = glfwGetJoystickButtons(joy, &count);

	uint8_t result = buttons[0] == 1 || (t && buttons[2] == 1);
	result |= (buttons[1] == 1 || (t && buttons[3] == 1)) << 1;
	result |= (buttons[6] == 1) << 2;
	result |= (buttons[7] == 1) << 3;
	result |= (axes[1] < -0.5f) << 4;
	result |= (axes[1] > 0.5f) << 5;
	result |= (axes[0] < -0.5f) << 6;
	result |= (axes[0] > 0.5f) << 7;

	return result;
}

void PaError(const PaError e) {
	Pa_Terminate();
	std::cout << std::endl << "PortAudio eor:" << std::endl;
	std::cout << "Error code: " << e << std::endl;
	std::cout << "Error message: " << Pa_GetErrorText(e) << std::endl;

	if ((e == paUnanticipatedHostError)) {
		const PaHostErrorInfo* hostErrorInfo = Pa_GetLastHostErrorInfo();
		std::cout << "Host info eor code: " << hostErrorInfo->eorCode << std::endl;
		std::cout << "Host info eor message: " << hostErrorInfo->eorText << std::endl << std::endl;
	}
}

void pState(NES* n) {
	printf("\rSTATUS CPU PC=%hu APU DM=%hhu P1=%hhu P2=%hhu TR=%hhu NO=%hhu PPU BG=%hhu BL=%hhu SP=%hhu SL=%hhu",
	n->cpu->PC,
	n->apu->dmc.enabled,
	n->apu->pulse1.enabled,
	n->apu->pulse2.enabled,
	n->apu->triangle.enabled,
	n->apu->noise.enabled,
	n->ppu->flag_show_background,
	n->ppu->flag_show_left_background,
	n->ppu->flag_show_sprites,
	n->ppu->flag_show_left_sprites);
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: NES <rom file>" << std::endl;
		return EXIT_FAILURE;
	}

	char* SRAM_path = new char[strlen(argv[1]) + 1];
	strcpy(SRAM_path, argv[1]);
	strcat(SRAM_path, ".srm");

	std::cout << "Initializing NES..." << std::endl;
	NES* n = new NES(argv[1], SRAM_path);
	if (!n->initialized) return EXIT_FAILURE;

	std::cout << "Initializing PortAudio..." << std::endl;
	PaError e = Pa_Initialize();
	if (e != paNoError) {
		PaError(e);
		return EXIT_FAILURE;
	}

	PaStreamParameters outputParameters;
#ifdef _WIN32
	outputParameters.device = Pa_GetDefaultOutputDevice();
	// you can select a specific device this way
	//outputParameters.device = Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(PaHostApiTypeId::paWASAPI))->defaultOutputDevice;
#else
	outputParameters.device = Pa_GetDefaultOutputDevice();
#endif

	if (outputParameters.device == paNoDevice) {
		std::ce << "ERROR: no PortAudio device found." << std::endl;
		PaError(e);
		return EXIT_FAILURE;
	}

	outputParameters.channelCount = 2;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = nullptr;

	std::cout << "Opening audio stream..." << std::endl;
	e = Pa_OpenStream(
		&n->apu->stream,
		nullptr,
		&outputParameters,
		44100,
		AUDIO_FRAME_BUFFER_SIZE,
		paNoFlag,
		nullptr,
		nullptr);

	if (e != paNoError) {
		PaError(e);
		return EXIT_FAILURE;
	}

	std::cout << "Initializing GLFW" << std::endl;
	if (!glfwInit()) {
		std::ce << "ERROR: Failed to initialize GLFW. Aborting." << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	std::cout << "Initializing GLFW window" << std::endl;
	GLFWwindow* window;
	if (fullscreen) {
		GLFWmonitor* const primary = glfwGetPrimaryMonitor();
		const GLFWvidmode* const mode = glfwGetVideoMode(primary);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		window = glfwCreateWindow(mode->width, mode->height, "NES", primary, nullptr);
		std::cout << "Fullscreen framebuffer created." << std::endl;
	}
	else {
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		window = glfwCreateWindow(256 * display_scale_factor, 240 * display_scale_factor, "NES", nullptr, nullptr);
		std::cout << "Window created." << std::endl;
	}

	if (!window) {
		std::ce << "ERROR: Failed to create window. Aborting." << std::endl;
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (v_sync) {
		// wait 1 sync to flip buffer (V_SYNC)
		glfwSwapInterval(1);
		std::cout << "V_SYNC enabled." << std::endl;
	}
	else {
		// sync immediately for lower latency
		// may introduce tearing
		glfwSwapInterval(0);
		std::cout << "V_SYNC disabled." << std::endl;
	}

	int old_w, old_h, w, h;
	glfwGetFramebufferSize(window, &old_w, &old_h);
	std::cout << "Framebuffer reports initial dimensions " << old_w << "x" << old_h << '.' << std::endl;

	std::cout << "Creating display texture" << std::endl;
	GLuint texture;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// decrease pops on linux
#ifdef __linux__
	PaAlsa_EnableRealtimeScheduling(n->apu->stream, 1);
#endif

	std::cout << "Starting audio stream" << std::endl;
	Pa_StartStream(n->apu->stream);
	if (e != paNoError) {
		PaError(e);
		return EXIT_FAILURE;
	}

	double prevtime = 0.0;
	while (!glfwWindowShouldClose(window)) {
		const double time = glfwGetTime();
		const double dt = time - prevtime < 1.0 ? time - prevtime : 1.0;
		prevtime = time;

		const bool t = (n->ppu->frame % 6) < 3;
		glfwPollEvents();
		n->controller1->buttons = getKeyboard(window, t) | getJoystick(GLFW_JOYSTICK_1, t);
		n->controller2->buttons = getJoystick(GLFW_JOYSTICK_2, t);

		if ((n->ppu->frame & 3) == 0) pState(n);

		// step the NES state forward by 'dt' seconds, or more if in fast-forward
		emulate(n, getKey(window, GLFW_KEY_GRAVE_ACCENT) ? 4.0 * dt : dt);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 240, 0, GL_RGBA, GL_UNSIGNED_BYTE, n->ppu->front);
		glfwGetFramebufferSize(window, &w, &h);
		if (w != old_w || h != old_h) {
			old_w = w;
			old_h = h;
			std::cout << std::endl << "Framebuffer reports resize to " << w << "x" << h << '.' << std::endl;
		}

		const float s1 = static_cast<float>(w) / 256.0f;
		const float s2 = static_cast<float>(h) / 240.0f;

		const float x = (s1 >= s2) ? s2 / s1 : 1.0f;
		const float y = (s1 >= s2) ? 1.0f : s1 / s2;

		glViewport(0, 0, w, h);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-x, -y);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(x, -y);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(x, y);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-x, y);
		glEnd();

		glfwSwapBuffers(window);

		if (getKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	// save SRAM back to file
	if (n->cartridge->battery_present) {
		std::cout << std::endl << "Writing SRAM" << std::endl;
		FILE* fp = fopen(SRAM_path, "wb");
		if (fp == nullptr || (fwrite(n->cartridge->SRAM, 8192, 1, fp) != 1)) {
			std::cout << "WARN: failed to save SRAM file!" << std::endl;
		}
		else {
			fclose(fp);
		}
	}

	Pa_StopStream(n->apu->stream);
	Pa_CloseStream(n->apu->stream);
	glfwTerminate();

	std::cout << "Terminating PortAudio..." << std::endl;
	Pa_Sleep(500L);
	Pa_Terminate();

	return EXIT_SUCCESS;
}
