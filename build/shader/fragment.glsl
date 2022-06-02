#version 330 core

uniform sampler2D mTexture;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

out vec4 FragColor;

void main() {
   float ambientStrength = 0.5;
   vec3 lightColor = vec3(1.0, 1.0, 1.0);
   vec3 ambient = ambientStrength * lightColor;
   vec3 lightPos = vec3(0.0, 800.0, 0.0); 
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;
   vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);
   FragColor = texture(mTexture, TexCoord) * vec4(result, 1.0);
}
