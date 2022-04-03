# SourceMod AnyMap
A wrapper around Sourcemod's [StringMap](https://sourcemod.dev/#/adt_trie/methodmap.StringMap) and [StringMapSnapshot](https://sourcemod.dev/#/adt_trie/methodmap.StringMapSnapshot), made to accept `any` as keys

### Installation
- Add to your `include` folder

### Example usage

```cpp
#include <anymap>

public void OnPluginStart()
{
	AnyMap map = new AnyMap();

	// Writing
	map.SetString(1, "123");
	map.SetValue(2, 123);
	map.SetArray(3, { 1, 2, 3 }, 3);

	// Reading
	char str[5];
	if (!map.GetString(1, str, sizeof(str)))
	{
		PrintToServer("String not found");
	}

	int val;
	if (!map.GetValue(2, val))
	{
		PrintToServer("Value not found");
	}

	any arr[3];
	if (!map.GetArray(3, arr, sizeof(arr)))
	{
		PrintToServer("Array not found");
	}

	// Making a snapshot
	AnyMapSnapshot snap = map.Snapshot();
	int maxKeys = snap.Length;

	// Iterating the snapshot
	for (int i = 0; i < maxKeys; i++)
	{
		any key = snap.GetKey(i);
		PrintToServer("Found key: %d", key);
	}

	// Freeing the handles
	delete snap;
	delete map;
}
```
