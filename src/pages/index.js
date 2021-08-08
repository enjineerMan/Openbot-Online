import React from 'react';
import Arrows from "../components/arrows.js";

const Home = () => {
  return (
    <div
      style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '80vh'
      }}
    >
      <Arrows />
    </div>
  );
};

export default Home;
