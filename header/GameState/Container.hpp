#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <Component.hpp>

#include <vector>
#include <memory>


namespace GUI
{

    class Container : public Component
    {

    public:
        typedef std::shared_ptr<Container> Ptr;

        enum Type {
            TopDown,
            LeftRight,
        };


    public:
        Container(Type _type);

        void				pack(Component::Ptr component);

        virtual bool		isSelectable() const;
        virtual void		handleEvent(const sf::Event& event);

        int                 getSelectedChild();
        void                setOpen(int index, bool flag);


    private:
        virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool				hasSelection() const;
        void				select(std::size_t index);
        void				selectNext();
        void				selectPrevious();
        Type                type;


    private:
        std::vector<Component::Ptr>		mChildren;
        int								mSelectedChild;
    };

}

#endif // BOOK_CONTAINER_HPP