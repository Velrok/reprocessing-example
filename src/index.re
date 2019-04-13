open Reprocessing;

type fruitState = Whole | Slice;
type size = {width: int, height: int};
type fruit = {
  pos:(int, int),
  img:glEnvT => imageT,
  state: fruitState,
  size: size
};
type gameState = { fruits: array(fruit) };


let setup = (env) => {
  Env.size(~width=600, ~height=600, env);

  let smallFruitSize = {width:100, height:100};
  let bananaImg = Draw.loadImage(~filename="./assets/banana_small.png");

  let banana = {
    pos: (50, 50),
    img: bananaImg,
    state: Whole,
    size: smallFruitSize
  };

  {fruits: [|banana|]};
};

//let slices = (fruit, mouse) => {
//  let mouseX, mouseY = mouse.pos;
//  let fX, fY = fruit.pos;
//  //if mouseX >= fX and mouseX <= fx
//}

let drawFruit = (env, fruit) => {
  Draw.fill(Constants.red, env);
  Draw.image(fruit.img(env),
             ~pos=fruit.pos,
             ~width=100,
             ~height=100,
             env);
};

let draw = (state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  let mouse = env.mouse;
  Draw.fill(Constants.blue, env);
  Draw.rect(~pos=mouse.pos, ~width=10, ~height=10, env);
  //print_endline();
  Array.iter(drawFruit(env), state.fruits);
  state;
};

run(~setup, ~draw, ());
