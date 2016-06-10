//
// Created by Wouter Posdijk on 09/06/16.
//

#include "MixingEffect.h"
#include "../../Util/HueConverter.h"

MixingEffect::MixingEffect(const std::shared_ptr<LightPerson> &person1, const std::shared_ptr<LightPerson> &person2)
        : person1(person1), person2(person2),
          prevColor1(sf::Color::Transparent),
          currentColor1(HueConverter::ToColor(person1->hue.getCenter())),
          prevColor2(sf::Color::Transparent),
          currentColor2(HueConverter::ToColor(person2->hue.getCenter())),
          stepColor1(currentColor1),
          stepColor2(currentColor2)
{ }

void MixingEffect::update(float dt) {
    leftInCycle -= dt;
    if(leftInCycle < 0){
        leftInCycle = cycle;
        prevColor1 = currentColor1;
        currentColor1 = HueConverter::ToColor(person1->hue.getCenter());
        stepColor1 = currentColor1;
        prevColor2 = currentColor2;
        currentColor2 = HueConverter::ToColor(person2->hue.getCenter());
        stepColor2 = currentColor2;
    }
    currentColor1.r -= stepColor1.r*dt/cycle*.3f;
    currentColor1.g -= stepColor1.g*dt/cycle*.3f;
    currentColor1.b -= stepColor1.b*dt/cycle*.3f;
    currentColor2.r -= stepColor2.r*dt/cycle*.3f;
    currentColor2.g -= stepColor2.g*dt/cycle*.3f;
    currentColor2.b -= stepColor2.b*dt/cycle*.3f;
}

void MixingEffect::draw(sf::RenderTarget &target) {

    //Calculate the axes
    Vector2 diff = person2->getLocation()-person1->getLocation();
    float dist = diff.size();

    sf::Vector2f x(diff.x/dist,diff.y/dist);
    sf::Vector2f y(-x.y,x.x);

    sf::VertexArray vertices(sf::Quads);

    sf::Vector2f p1Loc(person1->getLocation().x,person1->getLocation().y);
    sf::Vector2f p2Loc(person2->getLocation().x,person2->getLocation().y);

    float split = (1-leftInCycle/cycle)*dist;
    float thickness = 10.f;

    vertices.append(sf::Vertex(p1Loc,currentColor1));
    vertices.append(sf::Vertex(p1Loc+x*split,currentColor1));
    vertices.append(sf::Vertex(p1Loc+x*split-thickness*y,currentColor1));
    vertices.append(sf::Vertex(p1Loc-thickness*y,currentColor1));

    vertices.append(sf::Vertex(p1Loc+x*split,prevColor1));
    vertices.append(sf::Vertex(p2Loc,prevColor1));
    vertices.append(sf::Vertex(p2Loc-thickness*y,prevColor1));
    vertices.append(sf::Vertex(p1Loc+x*split-thickness*y,prevColor1));

    vertices.append(sf::Vertex(p2Loc,currentColor2));
    vertices.append(sf::Vertex(p2Loc-x*split,currentColor2));
    vertices.append(sf::Vertex(p2Loc-x*split+thickness*y,currentColor2));
    vertices.append(sf::Vertex(p2Loc+thickness*y,currentColor2));

    vertices.append(sf::Vertex(p2Loc-x*split,prevColor2));
    vertices.append(sf::Vertex(p1Loc,prevColor2));
    vertices.append(sf::Vertex(p1Loc+thickness*y,prevColor2));
    vertices.append(sf::Vertex(p2Loc-x*split+thickness*y,prevColor2));


    target.draw(vertices);
}