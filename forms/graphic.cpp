#include "forms/graphic.h"
#include "framework/data.h"
#include "framework/event.h"
#include "framework/framework.h"
#include "framework/image.h"
#include "framework/renderer.h"
#include "library/sp.h"
#include <tinyxml2.h>

namespace OpenApoc
{

Graphic::Graphic(sp<Image> Image)
    : Control(), image(Image), ImageHAlign(HorizontalAlignment::Left),
      ImageVAlign(VerticalAlignment::Top), ImagePosition(FillMethod::Fit), AutoSize(false)
{
}

Graphic::~Graphic() = default;

void Graphic::eventOccured(Event *e) { Control::eventOccured(e); }

void Graphic::onRender()
{
	if (!image)
	{
		return;
	}

	Vec2<float> pos = {0, 0};
	if (Vec2<unsigned int>(Size) == image->size)
	{
		fw().renderer->draw(image, pos);
	}
	else
	{
		switch (ImagePosition)
		{
			case FillMethod::Stretch:
				fw().renderer->drawScaled(image, pos, Size);
				break;

			case FillMethod::Fit:
				switch (ImageVAlign)
				{
					case VerticalAlignment::Top:
						pos.y = 0;
						break;
					case VerticalAlignment::Centre:
						pos.y = (Size.y - image->size.y) / 2;
						break;
					case VerticalAlignment::Bottom:
						pos.y = Size.y - image->size.y;
						break;
					default:
						LogError("Unknown ImageVAlign");
						return;
				}

				switch (ImageHAlign)
				{
					case HorizontalAlignment::Left:
						pos.x = 0;
						break;
					case HorizontalAlignment::Centre:
						pos.x = (Size.x - image->size.x) / 2;
						break;
					case HorizontalAlignment::Right:
						pos.x = Size.x - image->size.x;
						break;
					default:
						LogError("Unknown ImageHAlign");
						return;
				}

				fw().renderer->draw(image, pos);
				break;

			case FillMethod::Tile:
				for (pos.x = 0; pos.x < Size.x; pos.x += image->size.x)
				{
					for (pos.y = 0; pos.y < Size.y; pos.y += image->size.y)
					{
						fw().renderer->draw(image, pos);
					}
				}
				break;
		}
	}
}

void Graphic::update()
{
	Control::update();

	if (image && AutoSize)
	{
		Size = image->size;
	}
}

void Graphic::unloadResources()
{
	image.reset();
	Control::unloadResources();
}

sp<Image> Graphic::getImage() const { return image; }

void Graphic::setImage(sp<Image> Image) { image = Image; }

sp<Control> Graphic::copyTo(sp<Control> CopyParent)
{
	sp<Graphic> copy;
	if (CopyParent)
	{
		copy = CopyParent->createChild<Graphic>(this->image);
	}
	else
	{
		copy = mksp<Graphic>(this->image);
	}
	copy->ImageHAlign = this->ImageHAlign;
	copy->ImageVAlign = this->ImageVAlign;
	copy->ImagePosition = this->ImagePosition;
	copy->AutoSize = this->AutoSize;
	copyControlData(copy);
	return copy;
}

void Graphic::configureSelfFromXml(tinyxml2::XMLElement *Element)
{
	Control::configureSelfFromXml(Element);
	tinyxml2::XMLElement *subnode;
	UString attribvalue;

	if (Element->FirstChildElement("image") != nullptr)
	{
		image = fw().data->loadImage(Element->FirstChildElement("image")->GetText());
	}
	subnode = Element->FirstChildElement("alignment");
	if (subnode != nullptr)
	{
		if (subnode->Attribute("horizontal") != nullptr)
		{
			attribvalue = subnode->Attribute("horizontal");
			if (attribvalue == "left")
			{
				ImageHAlign = HorizontalAlignment::Left;
			}
			else if (attribvalue == "centre")
			{
				ImageHAlign = HorizontalAlignment::Centre;
			}
			else if (attribvalue == "right")
			{
				ImageHAlign = HorizontalAlignment::Right;
			}
		}
		if (subnode->Attribute("vertical") != nullptr)
		{
			attribvalue = subnode->Attribute("vertical");
			if (attribvalue == "top")
			{
				ImageVAlign = VerticalAlignment::Top;
			}
			else if (attribvalue == "centre")
			{
				ImageVAlign = VerticalAlignment::Centre;
			}
			else if (attribvalue == "bottom")
			{
				ImageVAlign = VerticalAlignment::Bottom;
			}
		}
	}
	subnode = Element->FirstChildElement("imageposition");
	if (subnode != nullptr)
	{
		if (subnode->GetText() != nullptr)
		{
			attribvalue = subnode->GetText();
			if (attribvalue == "stretch")
			{
				ImagePosition = FillMethod::Stretch;
			}
			else if (attribvalue == "fit")
			{
				ImagePosition = FillMethod::Fit;
			}
			else if (attribvalue == "tile")
			{
				ImagePosition = FillMethod::Tile;
			}
		}
	}
	subnode = Element->FirstChildElement("autosize");
	if (subnode != nullptr)
	{
		if (subnode->QueryBoolText(&AutoSize) != tinyxml2::XML_SUCCESS)
		{
			LogError("Unknown AutoSize attribute");
		}
	}
}
}; // namespace OpenApoc
