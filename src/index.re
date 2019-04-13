open Reprocessing;

type fruit = {x:int, y:int}

type gameState = { fruits: array(fruit) }

let bananna = {x: 50, y: 50}
let initialGameState = {fruits: [|bananna|]};

let setup = (env) => {
  Env.size(~width=600, ~height=600, env);
};


let drawFruit = (env, fruit) => {
  Draw.fill(Constants.red, env);
  Draw.rect(~pos=(fruit.x, fruit.y), ~width=150, ~height=150, env);
  ();
};

let draw = (_state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  Array.iter(drawFruit(env), initialGameState.fruits);
};

run(~setup, ~draw, ());
