#pragma once
#include <BML/BMLAll.h>
#include <cmath>
#include <memory>

extern "C" {
	__declspec(dllexport) IMod* BMLEntry(IBML* bml);
}

class Speedometer: public IMod
{
public:
	Speedometer(IBML* bml) : IMod(bml), last_position_(0, 0, 0) {}

	virtual CKSTRING GetID() override { return "Speedometer"; }
	virtual CKSTRING GetVersion() override { return "0.0.1"; }
	virtual CKSTRING GetName() override { return "Speedometer"; }
	virtual CKSTRING GetAuthor() override { return "Swung0x48"; }
	virtual CKSTRING GetDescription() override { return "Speedometer"; }
	DECLARE_BML_VERSION;

private:
	void OnLoad() override;
	void OnProcess() override;
	void OnLoadObject(CKSTRING filename, BOOL isMap, CKSTRING masterName,
		CK_CLASSID filterClass, BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials,
		BOOL dynamic, XObjectArray* objArray, CKObject* masterObj) override;
	void OnStartLevel() override;
	CK3dObject* get_current_ball();
private:
	VxVector last_position_;
	std::unique_ptr<BGui::Label> speed_label_;
	char display_[100];
};

