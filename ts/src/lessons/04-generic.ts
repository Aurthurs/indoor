interface KeyMap<K, V> {
  key: K;
  value: V;
}

type StringKeyMap = KeyMap<string, unknown>;

let stringKeyMap: StringKeyMap = {
  key: "name",
  value: "John",
};

let numberKeyMap: KeyMap<number, unknown> = {
  key: 1,
  value: "One",
};
