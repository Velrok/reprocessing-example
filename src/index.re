open Reprocessing;

type fruit = {x:int, y:int, img:glEnvT => imageT}
type gameState = { fruits: array(fruit) }

let bananaImg = Draw.loadImage(~filename="./assets/banana_small.png");
let banana = {x: 50, y: 50, img: bananaImg};
let initialGameState = {fruits: [|banana|]};

let setup = (env) => {
  Env.size(~width=600, ~height=600, env);
};


let drawFruit = (env, fruit) => {
  Draw.fill(Constants.red, env);
  //Draw.rect(~pos=(fruit.x, fruit.y), ~width=100, ~height=100, env);
  Draw.image(fruit.img(env),
             ~pos=(fruit.x, fruit.y),
             ~width=100,
             ~height=100,
             env);
};

let draw = (_state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  Array.iter(drawFruit(env), initialGameState.fruits);
};

run(~setup, ~draw, ());
