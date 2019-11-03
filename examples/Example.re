open ReactGridDnd;

type item = {
  id: int,
  name: string,
};

type itemState = {
  left: array(item),
  right: array(item),
};

let initialState = () => [|
  {id: 1, name: "ben"},
  {id: 2, name: "joe"},
  {id: 3, name: "jason"},
  {id: 4, name: "chris"},
  {id: 5, name: "heather"},
  {id: 6, name: "Richard"},
|];


module App = {
  [@react.component]
  let make = () => {
    let (items, setItems) = React.useState(initialState);

    let onChange = (~sourceId, ~sourceIndex, ~targetIndex, ~targetId) => {
      let result =
        GridUtil.swap(
          ~itemArray=items,
          ~moveIndex=sourceIndex,
          ~toIndex=targetIndex,
        );

      setItems(_ => result);
    };

    <GridContextProvider onChange>
      <div className="container">
        <GridDropZone
          className="dropzone left" id="left" boxesPerRow=4 rowHeight=70>
          {React.array(
             Belt.Array.map(items, item =>
               <GridItem key={string_of_int(item.id)}>
                 <div className="grid-item">
                   <div className="grid-item-content">
                     {React.string(
                        item.name
                        ->Js.String.slice(~from=0, ~to_=1)
                        ->Js.String.toLowerCase,
                      )}
                   </div>
                 </div>
               </GridItem>
             ),
           )}
        </GridDropZone>
      </div>
    </GridContextProvider>;
  };
}


ReactDOMRe.renderToElementWithId(<App />, "root");