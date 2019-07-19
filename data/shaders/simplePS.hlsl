struct PSin {
    float4 pos : SV_POSITION;
    float2 texCoord : ATTRIB1;
};

SamplerState gSamplerState : register(s0);
Texture2D gDiffuseMap : register(t0);

float4 main(PSin psin) : SV_TARGET {
    return gDiffuseMap.Sample(gSamplerState, psin.texCoord);
}