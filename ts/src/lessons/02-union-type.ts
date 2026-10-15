interface Bee {
  name: string;
}

interface Shark {
  speed: number;
}

type Animal = Bee & Shark;

let animal: Animal = {
  name: "Bee",
  speed: 10,
};

console.log(animal);
