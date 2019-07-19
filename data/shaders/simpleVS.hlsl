struct VSin {
    float3 pos : ATTRIB0;
    float2 texCoord : ATTRIB1;
};

struct PSin {
    float4 pos : SV_POSITION;
    float2 texCoord : ATTRIB1;
};

cbuffer CBDataVS : register(b0) {
    matrix gWorldMat;
    matrix gViewMat;
    matrix gProjMat;
    float2 gUVOffset;
    float2 gUVSize;
}

PSin main(VSin vsin) {
    PSin psin;
    psin.pos = float4(vsin.pos, 1.0f);
    psin.pos = mul(psin.pos, gWorldMat);
    psin.pos = mul(psin.pos, gViewMat);
    psin.pos = mul(psin.pos, gProjMat);
    psin.texCoord = vsin.texCoord*gUVSize + gUVOffset;
    return psin;
}