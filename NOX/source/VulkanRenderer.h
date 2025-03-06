#pragma once
#include "commonVk.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <glm/glm.hpp>

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

struct Vertex
{
	glm::vec2 pos;
	glm::vec3 color;

	static auto getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription;
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static auto getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions;

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

static void checkVkResult(VkResult err);

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VulkanRenderer
{

public:

private:
	const uint32_t WIDTH = 1024;
	const uint32_t HEIGHT = 768;
	uint32_t imageCount = 0;

	GLFWwindow* window = nullptr;

	VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
	VkAllocationCallbacks* allocator = VK_NULL_HANDLE;
	VkInstance instance = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkRenderPass renderPass = VK_NULL_HANDLE;
	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
	VkPipeline graphicsPipeline = VK_NULL_HANDLE;
	VkPipelineCache graphicsPipelineCache = VK_NULL_HANDLE;
	VkSwapchainKHR swapChain = VK_NULL_HANDLE;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	std::vector<VkCommandBuffer> commandBuffers;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	VkDebugUtilsMessengerEXT debugMessenger;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
	size_t currentFrame{0};
	bool framebufferResized = false;

	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif // NDEBUG



public:
	void run();

	void mainLoop();

	void initWindow();
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	void initVulkan();
	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void deviceWaitIdle();
	void pickPhysicalDevice();
	void createLogicalDevice();

	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	int rateDeviceSuitability(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	void createImageViews();

	void checkExtensions(const char** used_extensions, uint32_t count);
	std::vector<const char*> getRequiredExtensions();
	bool checkValidationLayerSupport();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
		VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createVertexBuffer();
	void createIndexBuffer();
	void createGraphicsPipeline();
	void createDescriptorPool();
	void createRenderPass();

	void createFramebuffers();

	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void createSyncObjects();

	void drawFrame();

	void cleanup();

	void recreateSwapChain();
	void cleanupSwapChain() const;
	
	GLFWwindow* getWindow();

	void setupImGuiBackends();

	uint32_t findMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties) const;
	
};
