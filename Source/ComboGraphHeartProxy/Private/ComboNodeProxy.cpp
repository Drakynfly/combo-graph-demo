#include "ComboNodeProxy.h"

#include "Graph/ComboGraphNodeBase.h"

FText UComboNodeProxyBase::GetNodeTitle() const
{
	if (ComboNode.LoadSynchronous())
	{
		return ComboNode->GetNodeTitle();
	}

	return FText();
}
