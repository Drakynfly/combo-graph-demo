#include "HeartGraphNode_ComboProxy.h"

#include "ComboNodeProxy.h"
#include "NativeGameplayTags.h"

struct FHeartComboProxyTags : public FGameplayTagNativeAdder
{
	FHeartGraphPinTag ComboProxyPin;

	virtual void AddTags() override
	{
		ComboProxyPin = FHeartGraphPinTag::AddNativeTag("Combo");
	}

	FORCEINLINE static const FHeartComboProxyTags& Get() { return HeartComboProxyTags; }

private:
	static FHeartComboProxyTags HeartComboProxyTags;
};

FHeartComboProxyTags FHeartComboProxyTags::HeartComboProxyTags;

UHeartGraphNode_ComboProxy::UHeartGraphNode_ComboProxy()
{
	auto&& SparseClassStruct = GetHeartGraphNodeSparseClassData();

	SparseClassStruct->DefaultPins.Empty();

	FHeartGraphPinDesc InputPin;
	InputPin.Name = "Inputs";
	InputPin.Direction = EHeartPinDirection::Input;
	InputPin.Tag = FHeartComboProxyTags::Get().ComboProxyPin;

	FHeartGraphPinDesc OutputPin;
	OutputPin.Name = "Outputs";
	OutputPin.Direction = EHeartPinDirection::Output;
	OutputPin.Tag = FHeartComboProxyTags::Get().ComboProxyPin;

	SparseClassStruct->DefaultPins.Add(InputPin);
	SparseClassStruct->DefaultPins.Add(OutputPin);
}

FText UHeartGraphNode_ComboProxy::GetNodeTitle_Implementation(const UObject* Node, EHeartNodeNameContext Context) const
{
	if (Context == EHeartNodeNameContext::NodeInstance)
	{
		if (auto&& ComboProxy = GetNodeObject<UComboNodeProxyBase>())
		{
			return ComboProxy->GetNodeTitle();
		}
	}

	return Super::GetNodeTitle_Implementation(Node, Context);
}

FText UHeartGraphNode_ComboProxy::GetNodeCategory_Implementation(const UObject* Node) const
{
	return FText::FromString("ComboNodeProxies");
}

bool UHeartGraphNode_ComboProxy::CanCreate_Implementation() const
{
	return true;
	//return false;
}
