import React, { useState, useCallback } from 'react';
import publish from "./publish.js";
import { AiFillCaretDown, AiFillCaretLeft, AiFillCaretRight, AiFillCaretUp } from "react-icons/ai";
import "styles/arrows.css";

const Arrows = ({}) => {
  // Declare a new state variable, which we'll call "count"
  const escFunction = useCallback((event) => {
    if(event.keyCode === 37) {
      //Do whatever when esc is pressed
    }
  }, []);
  return (
    <div>
    <button className="left" onClick={publish}>
      <AiFillCaretLeft className="arrow-icon" size={40}/>
    </button>
    <button className="right" onClick={publish}>
      <AiFillCaretRight className="arrow-icon" size={40}/>
    </button>
    <button className="down" onClick={publish}>
    <AiFillCaretDown className="arrow-icon" size={40}/>
    </button>
    <button className="up" onClick={publish}>
    <AiFillCaretUp className="arrow-icon" size={40}/>
    </button>
  </div>
  );
};

export default Arrows;