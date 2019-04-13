open Reprocessing;

type fruitState = Whole | Slice;
type size = {width: int, height: int};

type velocity = (int, int);
let gravity = 1;

type fruitImage = {whole: imageT, splat: imageT};
type fruit = {
  pos:(int, int),
  velocity: velocity,
  img:fruitImage,
  state: fruitState,
  size: size
};
type gameState = { fruits: array(fruit) };


let setup = (env) => {
  Env.size(~width=600, ~height=600, env);

  let smallFruitSize = {width:100, height:100};
  let bananaImg       = Draw.loadImage(~filename="./assets/banana_small.png", env);
  let bananaSplashImg = Draw.loadImage(~filename="./assets/splash_yellow_small.png", env);

  let banana = {
    pos: (0, 0),
    velocity: (0,1),
    img: {whole: bananaImg, splat: bananaSplashImg},
    state: Whole,
    size: smallFruitSize
  };

  {fruits: [|banana|]};
};

let cutting = (mousePos, fruit) => {
  switch(fruit.state) {
    | Slice => Slice
    | Whole => {
      let (mouseX, mouseY) = mousePos;
      let (fX, fY) = fruit.pos;
      let {width as w, height as h} = fruit.size;
      ((mouseX >= fX && mouseX <= (fX + w))
       && (mouseY >= fY && mouseY <= (fY + h))) ? Slice : Whole;
    }
  }
}

let drawFruit = (env, fruit) => {
  Draw.fill(Constants.red, env);
  let f = (img) => {
    Draw.image(img,
               ~pos=fruit.pos,
               ~width=100,
               ~height=100,
               env)
  }

  switch(fruit.state){
  | Whole => f(fruit.img.whole);
  | Slice => f(fruit.img.splat);
  }
};

let updateFruit = (mousePos, fruit) => {
  let (posX, posY) = fruit.pos;
  let (velX, velY) = fruit.velocity;
  {...fruit,
    pos: (posX + velX, posY + velY),
    state: cutting(mousePos, fruit)};
};

let draw = (state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  let mouse = env.mouse;
  //Draw.fill(Constants.blue, env);
  //Draw.rect(~pos=mouse.pos, ~width=10, ~height=10, env);
  //print_endline();
  let updatedFruits = Array.map(updateFruit(mouse.pos),state.fruits)
  Array.iter(drawFruit(env), updatedFruits);
  {fruits: updatedFruits};
};

run(~setup, ~draw, ());
