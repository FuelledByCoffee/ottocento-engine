#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable
#extension GL_EXT_shader_explicit_arithmetic_types_int64 : enable
#extension GL_EXT_buffer_reference : require

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 normalMatrix;
    mat4 view;
    mat4 proj;
    mat4 inverseproj;
    vec3 cameraPos;
    uint64_t edgeBuffer;
} ubo;
layout(binding = 1) uniform sampler2D texSampler[1024];

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPosition;
layout(location = 3) in float lightIntensity;

layout(location = 4) in vec3 viewSpace;
layout(location = 5) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform PushConstantData {
    vec3 offset;
    vec3 color;
    uint textureID;
} push;

float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    if (texture(texSampler[push.textureID], fragTexCoord).a == 0.0)
        outColor = vec4(vec3(0.7, 0.7, 0.7) * lightIntensity * clamp(rand(fragTexCoord), 0.82f, 1.0f), 1.0);
    else
    {
        vec4 texColor = texture(texSampler[push.textureID], fragTexCoord);
        vec3 modifiedColor = texColor.rgb * lightIntensity;
        vec4 finalColor = vec4(modifiedColor, texColor.a);
        outColor = finalColor;
    }
}