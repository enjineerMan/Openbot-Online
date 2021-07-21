import "./App.css";
import publish from "./components/publish.js";
import { AiFillCaretDown, AiFillCaretLeft, AiFillCaretRight, AiFillCaretUp } from "react-icons/ai";
import React, {Component} from "react";

class App extends Component {
  render() {
    return (
      <div>
        <button className="left" onClick={publish}>
          <AiFillCaretLeft className="arrow-icon" size={40}/>
        </button>
        <button className="right" onClick={publish}>
          <AiFillCaretRight className="arrow-icon" size={40}/>
        </button>
      </div>);
  }

}

export default App;
