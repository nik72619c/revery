open BenchFramework;

open Revery.UI;

let options = Reperf.Options.create(~iterations=10000, ());

let createNode = () => {
  let _ = (new node)();
  ();
};

let setupNode = (~style, ()) => {
  let n = (new node)();
  n#setStyle(style);
  n;
};

let rec setupNodeTree =
        (
          ~depth: int,
          ~breadth: int,
          ~style=Style.make(~width=400, ~height=400, ()),
          (),
        ) => {
  let i = ref(breadth);

  let n = setupNode(~style, ());

  while (i^ > 0 && depth > 0) {
    let newNode = setupNodeTree(~depth=depth - 1, ~breadth, ());
    n#addChild(newNode);

    decr(i);
  };

  n;
};

let layoutNode = (n: node) => {
  Layout.layout(n, 1.0, 1);
};

bench(
  ~name="Node: create single node",
  ~options,
  ~setup=() => (),
  ~f=createNode,
  (),
);

bench(
  ~name="Layout: layout single node",
  ~options,
  ~setup=setupNode(~style=Style.make(~width=100, ~height=100, ())),
  ~f=layoutNode,
  (),
);

bench(
  ~name="Layout: layout node tree (4 deep, 4 wide)",
  ~options,
  ~setup=setupNodeTree(~depth=4, ~breadth=4),
  ~f=layoutNode,
  (),
);
bench(
  ~name="Layout: layout node tree (4 deep, 4 wide) - minimal layout",
  ~options,
  ~setup=
    setupNodeTree(
      ~depth=4,
      ~breadth=4,
      ~style=
        Style.make(
          ~width=400,
          ~height=400,
          ~layoutMode=Style.LayoutMode.Minimal,
          (),
        ),
    ),
  ~f=layoutNode,
  (),
);
