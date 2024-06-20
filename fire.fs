#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D uDiffuseSampler;
uniform float uvAlphaTime; // Tiempo

// Función para generar ruido para la componente x o y
float generateNoise(vec2 uv, float time, vec2 offset, float scale) {
    vec2 uvOffset = uv + time * offset * 1.5; // Aumentar el factor de offset
    float noise = (texture(uDiffuseSampler, uvOffset * scale).w - 0.5) * 2.0;
    return noise;
}

// Main function
void main()
{
    vec2 uv = TexCoord;
    float time = uvAlphaTime;
    
    // Genera valor de ruido para x
    float noiseX = generateNoise(uv, time, vec2(0.02, 0.73), 1.6); // Modificar los valores de offset y escala
    
    // Genera valor de ruido para y
    float noiseY = generateNoise(uv, time, vec2(-0.02, 0.31), 0.8); // Modificar los valores de offset y escala
    
    // Combina los valores de ruido para x e y
    vec2 finalNoise = vec2(noiseX, noiseY);
    float perturbFactor = (1.0 - uv.y) * 0.7 + 0.1; // Modifica el factor de perturbación
    finalNoise = (finalNoise * perturbFactor) + uv - 0.06; // Ajustar el offset final

    // Obtiene el color base y el valor alfa de la textura usando las coordenadas UV originales
    vec4 baseColor = texture(uDiffuseSampler, uv);
    float alphaValue = baseColor.b; // Usar el canal azul para el valor alfa

    // Aplica ruido al alfa para crear un efecto de llama más realista
    alphaValue *= clamp(1.0 - length(finalNoise - uv) * 1.8, 0.0, 1.0); // Modifica el factor de influencia del ruido

    // Suaviza los bordes de la llama usando smoothstep
    alphaValue = smoothstep(0.05, 0.7, alphaValue); // Modifica los valores de suavizado

    // Combina el color base con las UVs de ruido finales
    vec4 finalColor = texture(uDiffuseSampler, finalNoise);
    finalColor = vec4(finalColor.r * 2.0, finalColor.g * 0.9, (finalColor.g / finalColor.r) * 0.2, alphaValue);

    FragColor = finalColor;
}
