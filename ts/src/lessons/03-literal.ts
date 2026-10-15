// 字符串字面量
let s: "active" | "inactive";
s = "active";

// 数字字面量
let n: 1 | 2 | 3;
n = 1;

// 联合类型
interface SuccessResponse {
  status: "success";
  data: any;
}

interface FailureResponse {
  status: "failure";
  error: string;
}

type ApiResponse = SuccessResponse | FailureResponse;

let response: ApiResponse = {
  status: "success",
  data: "Hello, TypeScript!",
};

console.log(response);
