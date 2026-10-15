interface User {
  id: number;
  name: string;
}

// 普通函数，返回 Promise<User>类型
function getUserData(id: number): Promise<User> {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (id > 0) {
        resolve({ id, name: "John Doe" });
      } else {
        reject(new Error("无效的用户ID"));
      }
    }, 1000);
  });
}

// async 函数自动返回 Promise，不需要显式声明返回类型
async function addMoney(m: number) {
  return m + 100;
}

// 两者的目的都是一致的，我建议后者以示区分
async function main(): Promise<void> {
  try {
    const user = await getUserData(1)
      .then((user) => console.log("获取成功:", user))
      .finally(() => console.log("完成"));

    const money = await addMoney(10)
      .then((money) => console.log("增加成功:", money))
      .finally(() => console.log("完成"));
  } catch (error) {
    if (error instanceof Error) {
      console.error("发生错误:", error.message);
    }
  }
}

// 并发执行
async function parallel() {
  const p1 = getUserData(1);
  const p2 = getUserData(2);

  const [user1, user2] = await Promise.all([p1, p2]);
  console.log(user1, user2);
}
