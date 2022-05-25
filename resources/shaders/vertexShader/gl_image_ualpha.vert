#verision 450 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out vec4 F_Color;

// 可以考虑将这个结果计算完成传进来
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position,1.0);
    F_Color = vec4(color,1.0);
}