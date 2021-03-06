struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 colour : TEXCOORD1;
};

Texture2D tex;
SamplerState samplerState;

float4 main(PixelInput input) : SV_TARGET
{
    return tex.Sample(samplerState, input.uv) * input.colour;
}