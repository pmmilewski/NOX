#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	//outColor = vec4(fragColor * ((fragTexCoord.x + fragTexCoord.y)/2.0), 1.0);
	//outColor = texture(texSampler, fragTexCoord);
	outColor = vec4(fragColor* clamp(0.5f + texture(texSampler, fragTexCoord).rgb, 0.0f, 1.0f), 1.0);
}