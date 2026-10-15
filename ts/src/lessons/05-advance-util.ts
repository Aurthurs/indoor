// 将类或者接口所有属性变为可选类型
interface Todo {
  id: string;
  title?: string;
  completed: boolean;
}

type PartialTodo = Partial<Todo>;

let partialTodo: PartialTodo = {
  id: "1",
};

/**
 * 同理：
 * - Required<Todo>：将类或者接口所有属性变为必选类型
 * - Readonly<Todo>：将类或者接口所有属性变为只读类型
 * - Pick<Todo, "id" | "title">：从类或者接口中选择指定属性
 * - Omit<Todo, "completed">：从类或者接口中排除指定属性
 * - Record<string, Todo>：将两个不同类型的属性结合在一起
 * - ReturnType<Todo>：返回函数的返回类型
 */

type RequiredTodo = Required<Todo>;

type ReadonlyTodo = Readonly<Todo>;

type PickTodo = Pick<Todo, "id" | "title">;

type OmitTodo = Omit<Todo, "completed">;

type Person = {
  name: string;
  age: number;
};

type City = "shangai" | "beijing";

type RecordPerson = Record<City, Person>;

function createPerson(name: string, age: number): Person {
  return { name, age };
}

type ReturnTypeCreatePerson = ReturnType<typeof createPerson>;
