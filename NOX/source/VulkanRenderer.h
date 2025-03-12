#pragma once
#include "commonVk.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <glm/glm.hpp>
#include "GameObject.h"

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

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
	glm::mat4 viewMatrix;
	std::vector<GameObject>* currentSceneObjects = nullptr;
	std::vector<Vertex> staticObjectsVertices;
	std::vector<uint16_t> staticObjectsIndices;

	GLFWwindow* window = nullptr;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;
	VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
	std::vector<VkDescriptorSet> descriptorSets;
	VkAllocationCallbacks* allocator = VK_NULL_HANDLE;
	VkInstance instance = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkRenderPass renderPass = VK_NULL_HANDLE;
	VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;
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
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
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
	void initWindow();
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createTextureImageView();
	void createTextureSampler();
	void createDepthResources();
	void createStaticGameObjectsData();
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
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	VkCommandBuffer beginSingleTimeCommands();
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
		VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void createTextureImage();
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();
	void createGraphicsPipeline();
	void createDescriptorSetLayout();
	void createDescriptorPool();
	void createDescriptorSets();
	void createRenderPass();

	void createFramebuffers();

	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void createSyncObjects();

	void updateUniformBuffer(uint32_t imageIndex) const;
	void drawFrame();

	void cleanup();

	void recreateSwapChain();
	void cleanupSwapChain() const;
	
	GLFWwindow* getWindow();

	void setupImGuiBackends();

	uint32_t findMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties) const;
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const;
	VkFormat findDepthFormat() const;
	bool hasStencilComponent(VkFormat format) const;

	void SetViewMatrix(const glm::mat4& vMatrix) { viewMatrix = vMatrix; };
	void SetCurrentScene(std::vector<GameObject>& scene) { currentSceneObjects = &scene; };
};
