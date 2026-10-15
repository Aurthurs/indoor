enum Normal {
  One = 2,
  Two,
  Three,
}

enum HttpStatus {
  SUCCESS = 200,
  ERROR = 500,
  NOT_FOUND = 404,
  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  FORBIDDEN = 403,
  INTERNAL_SERVER_ERROR = 500,
}

function nomalResponse(status: HttpStatus, message: string): string {
  return `Status: ${status}, Message: ${message}`;
}

const normalResponse = nomalResponse(HttpStatus.SUCCESS, "Success");
console.log(normalResponse);
