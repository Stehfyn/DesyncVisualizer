#pragma once

struct NetworkSettings
{
	float processingDelayMin = 0.0f;
	float processingDelayMax = 0.0f;
	float queuingDelayMin = 0.0f;
	float queuingDelayMax = 0.0f;
	float transmissionDelayMin = 0.0f;
	float transmissionDelayMax = 0.0f;
	float propagationDelayMin = 0.0f;
	float propagationDelayMax = 0.0f;
	float packetLossPct = 0.0f;
	int numHopsToServer = 0;

	float tickrate;
	float rttPlayer;
	float rttOther;
};
