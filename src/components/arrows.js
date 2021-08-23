import React, { useState, useEffect } from 'react';
import publish from "./publish.js";
import { AiFillCaretDown, AiFillCaretLeft, AiFillCaretRight, AiFillCaretUp } from "react-icons/ai";
import "../styles/arrowsStyles.css";
const Arrows = () => {
  var leftPressed = useKeyPress("ArrowLeft");
  var rightPressed = useKeyPress("ArrowRight");
  var upPressed = useKeyPress("ArrowUp");
  var downPressed = useKeyPress("ArrowDown");
var keyStates=(leftPressed? 1 : 0).toString() +  
              (rightPressed? 1 : 0).toString() + 
              (downPressed? 1 : 0).toString() + 
              (upPressed? 1 : 0).toString();

useEffect(()=>{
  keyStates=(leftPressed? 1 : 0).toString() +  
  (rightPressed? 1 : 0).toString() + 
  (downPressed? 1 : 0).toString() + 
  (upPressed? 1 : 0).toString();
  console.log(keyStates);
  publish(JSON.stringify(keyStates));
}, [leftPressed, rightPressed, upPressed, downPressed]);

return (
<div className="center"> 
  <div className="left" style={{backgroundColor:useKeyPress("ArrowLeft") ? "rgb(227, 171, 16)" : "rgb(245, 224, 120)"}}> 
    <AiFillCaretLeft className="arrow-icon" size={40}/> 
  </div> 
  <div className="right" style={{backgroundColor:useKeyPress("ArrowRight") ? "rgb(227, 171, 16)" : "rgb(245, 224, 120)"}}> 
    <AiFillCaretRight className="arrow-icon" size={40}/> </div> 
  <div className="down" style={{backgroundColor:useKeyPress("ArrowDown") ? "rgb(227, 171, 16)" : "rgb(245, 224, 120)"}}> 
    <AiFillCaretDown className="arrow-icon" size={40}/> 
  </div> 
  <div className="up" style={{backgroundColor:useKeyPress("ArrowUp") ? "rgb(227, 171, 16)" : "rgb(245, 224, 120)"}}> 
    <AiFillCaretUp className="arrow-icon" size={40}/> 
  </div> 
</div> 
); 
}; 

function useKeyPress(targetKey) {
  // State for keeping track of whether key is pressed
  const [keyPressed, setKeyPressed] = useState(false);

  // If pressed key is our target key then set to true
  function downHandler({ key }) {
    if (key === targetKey) {
      setKeyPressed(true);
    }
  }

  // If released key is our target key then set to false
  const upHandler = ({ key }) => {
    if (key === targetKey) {
      setKeyPressed(false);
    }
  };

  // Add event listeners
  useEffect(() => {
    window.addEventListener('keydown', downHandler);
    window.addEventListener('keyup', upHandler);
    // Remove event listeners on cleanup
    return () => {
      window.removeEventListener('keydown', downHandler);
      window.removeEventListener('keyup', upHandler);
    };
  }, [targetKey]); // Empty array ensures that effect is only run on mount and unmount

  return keyPressed;
}
export default Arrows;