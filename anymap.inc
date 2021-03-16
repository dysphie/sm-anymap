#include <sourcemod>

#pragma semicolon 1
#pragma newdecls required


methodmap AnyMapSnapshot < Handle
{
	public static any DecodeKey(char key[6])
	{
		return ((key[0] & ~0x80) << 28) | ((key[1] & ~0x80) << 21) | 
		((key[2] & ~0x80) << 14) | ((key[3] & ~0x80) << 7)  | (key[4] & ~0x80);
	}

	property int Length 
	{
		public get()
		{
			return view_as<StringMapSnapshot>(this).Length;
		}
	}

	public int GetKey(int index)
	{
		char encoded[6];
		view_as<StringMapSnapshot>(this).GetKey(index, encoded, sizeof(encoded));
		return AnyMapSnapshot.DecodeKey(encoded);
	}
};

methodmap AnyMap < Handle
{
	public AnyMap()
	{
		return view_as<AnyMap>(new StringMap());
	}

	public static void EncodeKey(any value, char dest[6])
	{
		dest[0] = view_as<char>(((value >>> 28) & 0x7F) | 0x80); 
		dest[1] = view_as<char>(((value >>> 21) & 0x7F) | 0x80); 
		dest[2] = view_as<char>(((value >>> 14) & 0x7F) | 0x80); 
		dest[3] = view_as<char>(((value >>> 7) & 0x7F) | 0x80);
		dest[4] = view_as<char>((value & 0x7F) | 0x80);
		dest[5] = '\0';
	}

	public AnyMap Clone()
	{
		return view_as<AnyMap>(view_as<StringMap>(this).Clone());
	}

	public bool SetValue(const any key, any value, bool replace=true)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).SetValue(encoded, value, replace);
	}

	public bool SetArray(const any key, const any[] array, int num_items, bool replace=true)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).SetArray(encoded, array, num_items, replace);
	}

	public bool SetString(const any key, const char[] value, bool replace=true)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).SetString(encoded, value, replace);
	}

	public bool GetValue(const any key, any &value)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).GetValue(encoded, value);
	}

	public bool GetArray(const any key, any[] array, int max_size, int &size=0)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).GetArray(encoded, array, max_size, size);
	}

	public bool GetString(const any key, char[] value, int max_size, int &size=0)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).GetString(encoded, value, max_size, size);
	}

	public bool ContainsKey(const any key)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).ContainsKey(encoded);
	}

	public bool Remove(const any key)
	{
		char encoded[6];
		AnyMap.EncodeKey(key, encoded);
		return view_as<StringMap>(this).Remove(encoded);
	}

	public void Clear()
	{
		view_as<StringMap>(this).Clear();
	}

	public AnyMapSnapshot Snapshot()
	{
		return view_as<AnyMapSnapshot>(view_as<StringMap>(this).Snapshot());
	}

	property int Size 
	{
		public get()
		{
			return view_as<StringMap>(this).Size;
		}
	}
};
