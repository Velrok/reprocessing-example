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
    pos: (0, 0),
    img: bananaImg,
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
  switch(fruit.state){
  | Whole => Draw.image(fruit.img(env),
             ~pos=fruit.pos,
             ~width=100,
             ~height=100,
             env);
  | Slice => ()

  }
};

let updateFruit = (mousePos, fruit) => {
  {...fruit, state: cutting(mousePos, fruit)};
};

let draw = (state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  let mouse = env.mouse;
  Draw.fill(Constants.blue, env);
  Draw.rect(~pos=mouse.pos, ~width=10, ~height=10, env);
  //print_endline();
  let updatedFruits = Array.map(updateFruit(mouse.pos),state.fruits)
  Array.iter(drawFruit(env), updatedFruits);
  {fruits: updatedFruits};
};

run(~setup, ~draw, ());
